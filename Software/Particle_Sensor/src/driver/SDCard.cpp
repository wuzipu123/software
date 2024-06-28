
#include "SDCard.h"
#include "mbed_debug.h"
#include "utils.h"

SDCard::SDCard(SDBlockDevice &sd_block_device, FATFileSystem &fat_file_system)
    : _n_detect(MBED_CONF_APP_SD_CARD_DETECT, PullUp),
      _sd_block_device(sd_block_device),
      _fat_file_system(fat_file_system),
      _initialized(false) {
}

mbed_error_status_t SDCard::init() {
  if (_initialized) {
    return MBED_SUCCESS;
  }

  if (!is_inserted()) {
    debug("No SD card detected\n");
    return MBED_ERROR_ITEM_NOT_FOUND;
  }

  if (MBED_SUCCESS != _sd_block_device.init()) {
    debug("Block device initialization of SD Card failed\n");
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  if (MBED_SUCCESS != _sd_block_device.frequency(MBED_CONF_APP_SDCARD_SPI_FREQUENCY)) {
    debug("Setting SPI frequency to %dHz for SD card failed\n", MBED_CONF_APP_SDCARD_SPI_FREQUENCY);
    _sd_block_device.deinit();
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  int error = _fat_file_system.mount(&_sd_block_device);
  if (MBED_SUCCESS != error) {
    debug("Mounting FAT filesystem of SD card failed: %d\n", error);
    _sd_block_device.deinit();
    return MBED_ERROR_INITIALIZATION_FAILED;
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
    debug("Formatting FAT filesystem of SD card failed: %d\n", error);
    return MBED_ERROR_FAILED_OPERATION;
  }

  TRY(deinit());

  return MBED_SUCCESS;
}

mbed_error_status_t SDCard::write(const std::string &filename, const std::string &data) {
  if (!_initialized) {
    debug("Write failed, because SDCard is not initialized\n");
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  mbed_error_status_t error_status = MBED_SUCCESS;
  std::string file_path = "/" + std::string(_fat_file_system.getName()) + "/" + filename;

  _sd_card_mutex.lock();
  FILE *fd = fopen(file_path.c_str(), "a+");
  if (nullptr != fd) {
    int error = fprintf(fd, "%s", data.c_str());
    if (error < 0) {
      debug("Writing data to file %s failed\n", file_path.c_str());
      error_status = MBED_ERROR_WRITE_FAILED;
    }
    error = fclose(fd);
    if (MBED_SUCCESS != error) {
      debug("Closing file %s failed\n", file_path.c_str());
      error_status = MBED_ERROR_CLOSE_FAILED;
    }
  } else {
    debug("Opening file %s failed\n", file_path.c_str());
    error_status = MBED_ERROR_OPEN_FAILED;
  }

  _sd_card_mutex.unlock();
  if (MBED_SUCCESS != error_status) {
    return error_status;
  }

  return check_available_memory();
}

mbed_error_status_t SDCard::deinit() {
  int error = _fat_file_system.unmount();
  if (MBED_SUCCESS != error) {
    debug("Unmounting FAT filesystem of SD card failed: %d\n", error);
    return MBED_ERROR_CLOSE_FAILED;
  } else {
    _sd_block_device.deinit();
  }

  _initialized = false;
  return MBED_SUCCESS;
}

mbed_error_status_t SDCard::check_available_memory() {
  struct statvfs stats = {};
  int error = _fat_file_system.statvfs(_fat_file_system.getName(), &stats);
  if (!error) {
    uint64_t available_memory_size = stats.f_bavail * stats.f_bsize;
    if (available_memory_size < 1048576ULL) {
      _is_full = true;
      debug("SD card is full\n");
      return MBED_ERROR_OUT_OF_MEMORY;
    } else {
      _is_full = false;
    }
  } else {
    return MBED_ERROR_FAILED_OPERATION;
  }
  return MBED_SUCCESS;
}

bool SDCard::is_full() {
  return _is_full;
}

bool SDCard::is_inserted() {
  return !_n_detect;
}