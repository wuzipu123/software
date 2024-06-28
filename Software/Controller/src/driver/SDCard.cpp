
#include "SDCard.h"
#include "utils.h"
#include <cstdio>

SDCard::SDCard(SDBlockDevice &sd_block_device, FATFileSystem &fat_file_system)
    : _sd_block_device(sd_block_device),
      _fat_file_system(fat_file_system),
      _initialized(false) {
}

mbed_error_status_t SDCard::init() {
  if (_initialized) {
    return MBED_SUCCESS;
  }

  if (MBED_SUCCESS != _sd_block_device.init()) {
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_BLOCK_DEVICE, MBED_ERROR_INITIALIZATION_FAILED);
    MBED_WARNING(error_status, "Block device initialization of SD Card failed");
    return error_status;
  }

  if (MBED_SUCCESS != _sd_block_device.frequency(MBED_CONF_APP_SDCARD_SPI_FREQUENCY)) {
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_BLOCK_DEVICE, MBED_ERROR_INITIALIZATION_FAILED);
    MBED_WARNING1(error_status, "Setting SPI frequency for SD card failed", MBED_CONF_APP_SDCARD_SPI_FREQUENCY);
    _sd_block_device.deinit();
    return error_status;
  }

  int error = _fat_file_system.mount(&_sd_block_device);
  if (MBED_SUCCESS != error) {
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_INITIALIZATION_FAILED);
    MBED_WARNING1(error_status, "Mounting FAT filesystem of SD card failed", error);
    _sd_block_device.deinit();
    return error_status;
  }

  mbed_error_status_t error_status = check_available_memory();
  if (MBED_SUCCESS != error_status) {
    _sd_block_device.deinit();
    return error_status;
  }

  _initialized = true;
  return MBED_SUCCESS;
}

mbed_error_status_t SDCard::format() {
  int error = mbed::FATFileSystem::format(&_sd_block_device, 4096);
  if (MBED_SUCCESS != error) {
    DEBUG_PRINTF("Formatting FAT filesystem of SD card failed: %d\n", error);
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_FAILED_OPERATION);
    MBED_WARNING1(error_status, "Formatting FAT filesystem of SD card failed", error);
    return error_status;
  }

  TRY(deinit());

  return MBED_SUCCESS;
}

mbed_error_status_t SDCard::write(const std::string &filename, const std::string &data) {
  if (!_initialized) {
    DEBUG_PRINT("Write failed, because SDCard is not initialized\n");
    return MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_INITIALIZATION_FAILED);
  }

  mbed_error_status_t error_status = MBED_SUCCESS;
  std::string file_path;
  file_path += "/" + std::string(_fat_file_system.getName()) + "/" + filename;

  FILE *fd = fopen(file_path.c_str(), "a+");
  if (nullptr != fd) {
    int error = fprintf(fd, "%s", data.c_str());
    if (error < 0) {
      DEBUG_PRINTF("Writing data to file %s failed\n", file_path.c_str());
      fflush(stdout);
      error_status = MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_WRITE_FAILED);
      MBED_WARNING1(error_status, "Writing data to file failed", error);
    }
    error = fclose(fd);
    if (MBED_SUCCESS != error) {
      DEBUG_PRINTF("Closing file %s failed\n", file_path.c_str());
      fflush(stdout);
      error_status = MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_CLOSE_FAILED);
      MBED_WARNING1(error_status, "Closing file failed", error);
    }
  } else {
    DEBUG_PRINTF("Opening file %s failed\n", file_path.c_str());
    fflush(stdout);
    error_status = MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_OPEN_FAILED);
    MBED_WARNING(error_status, "Opening file failed");
  }

  if (MBED_SUCCESS != error_status) {
    return error_status;
  }

  return check_available_memory();
}

mbed_error_status_t SDCard::deinit() {
  int error = _fat_file_system.unmount();
  if (MBED_SUCCESS != error) {
    DEBUG_PRINTF("Unmounting FAT filesystem of SD card failed: %d\n", error);
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_CLOSE_FAILED);
    MBED_WARNING1(error_status, "Unmounting FAT filesystem of SD card failed", error);
    return error_status;
  } else {
    _sd_block_device.deinit();
  }

  _initialized = false;
  return MBED_SUCCESS;
}

mbed_error_status_t SDCard::check_available_memory() {
  struct statvfs stats;
  int error = _fat_file_system.statvfs(_fat_file_system.getName(), &stats);
  if (!error) {
    uint64_t available_memory_size = stats.f_bavail * stats.f_bsize;
    if (available_memory_size < 1048576ULL) {
      _is_full = true;
      return MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_OUT_OF_MEMORY);
    } else {
      _is_full = false;
    }
  } else {
    return MBED_MAKE_ERROR(MBED_MODULE_FILESYSTEM, MBED_ERROR_FAILED_OPERATION);
  }
  return MBED_SUCCESS;
}

bool SDCard::is_full() {
  return _is_full;
}
