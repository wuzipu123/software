
#ifndef CONTROLLER_SDCARD_H
#define CONTROLLER_SDCARD_H

#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "mbed_error.h"
#include <string>

/**
 * Class handling the SD card operations
 */
class SDCard : private mbed::NonCopyable<SDCard> {
public:
  /**
   * Create a SDCard object with the given \p sd_block_device and
   * \p fat_file_system. Because the initialization of the SDCard can fail,
   * it is done in the init() function instead of the constructor.
   *
   * @param sd_block_device reference to the SDBlockDevice object
   * @param fat_file_system reference to the FATFileSystem object
   */
  SDCard(SDBlockDevice &sd_block_device, FATFileSystem &fat_file_system);

  /**
   * Initializes the #_sd_block_device, sets its SPI frequency, mounts the #_fat_file_system
   * and checks if more than 1MB free memory is available on the SD card.
   *
   * @return MBED_SUCCESS if initialization succeeded or SDCard is already initialized.
   *         Otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t init();

  /**
   * Deinitializes the SDCard object by unmounting #_fat_file_system
   * and deinitializing #_sd_block_device.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t deinit();

  /**
   * Formats the SD card with a cluster size of 4kB
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t format();

  /**
   * Writes the given \p data to the file with the given \p filename in append mode.
   * If the file with the \p filename does not exist, it is created.
   * The file is opened before the write operation and closed afterwards.
   * After the closing the file, the available free memory is checked.
   *
   * @param filename the name of the file to which the \p data should be appended
   * @param data     data string that should be written to the specified file
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t write(const std::string &filename, const std::string &data);

  /**
   * Check the available free memory on the SD card. If the SD card is full,
   * #_is_full is set to true.
   *
   * @return MBED_SUCCESS if memory statistics could be read and the available memory is
   *         more than 1MB. Otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t check_available_memory();

  /**
   * @return #_is_full
   */
  bool is_full();

private:
  /**
   * Flag which is set to true by check_available_memory() as soon as the SD card is full.
   */
  bool _is_full = false;

  /**
   * Reference to the SDBlockDevice object
   */
  SDBlockDevice &_sd_block_device;

  /**
   * Reference to the FATFileSystem object
   */
  FATFileSystem &_fat_file_system;

  /**
   * Flag which is true if the SDCard object is initialized
   */
  bool _initialized;
};


#endif //CONTROLLER_SDCARD_H
