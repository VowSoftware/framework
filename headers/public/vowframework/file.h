#ifndef VOW_GUARD_FILE
#define VOW_GUARD_FILE

////////////////////////////////////////////////////////////////////////////////
// Reads all text from a file.
//
// Parameters
//   * `path`: Absolute path to the file to read.
//
// Returns
//   * [Success] Pointer to the allocated text.
//   * [Failure] Null pointer.
////////////////////////////////////////////////////////////////////////////////
char* vow_file_read(const char* path);

#endif