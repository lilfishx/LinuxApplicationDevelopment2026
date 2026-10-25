# File Move Utility with File Protection

**This project provides a robust C-based file movement utility (`move`) paired with a dynamic shared library (`protect.so`) that prevents the accidental deletion of files containing "PROTECT" in their name.** It also includes a wrapper script (`safemove.sh`) to seamlessly run the move utility with the protection layer enabled via `LD_PRELOAD`.

## Core Features

* **Atomic-like File Moving:** Reads the source file into memory, writes it to the destination preserving the file mode, and deletes the original file.
* **Deletion Protection:** Intercepts the standard `remove()` function using `dlfcn` and `LD_PRELOAD` to safeguard critical files.
* **Automated Installation & Testing:** Equipped with a comprehensive `Makefile` and an automated test suite.
* **RPM Packaging Support:** Includes a complete `.spec` file configuration for building system-native packages.

---

## Project Structure

* `move.c` — Main application logic for moving a file.
* `protect.c` — Shared library source code used to override `remove()`.
* `safemove.sh` — Shell wrapper that injects `protect.so` into the execution of `move`.
* `Makefile` — Build automation configuration.
* `test.sh` — Test runner that executes individual edge-case scripts.
* `move.spec` — RPM package specification metadata.

---

## Installation & Deployment

### Prerequisites
Make sure you have a GCC compiler and standard development tools (`make`) installed.

### Standard Compilation
Build the binary and the shared library locally using the default recipe:
```bash
make
```

### System-Wide Installation
Install the application, wrapper script, and shared library into your system directories (defaults to `/usr/local`):
```bash
sudo make install
```
*Note: The install process automatically updates the path within `safemove.sh` to point to the newly installed system location of `protect.so`.*

### Building an RPM Package
To build a native RPM package using the provided `.spec` configuration:
1. Create a distribution archive:
   ```bash
   make tar
   ```
2. Move the generated `move-1.0.0.tar.gz` to your `rpmbuild/SOURCES/` directory.
3. Run the RPM build command:
   ```bash
   rpmbuild -ba move.spec
   ```

### Uninstallation
Remove all installed binaries and shared libraries from your system:
```bash
sudo make uninstall
```

---

## Usage

### Direct Usage (No Protection)
Moves `INFILE` to `OUTFILE` without checking for protected filenames.
```bash
./move path/to/infile path/to/outfile
```

### Safe Usage (With Protection Enabled)
Runs the move operation while protecting any file that contains the substring `"PROTECT"` from being deleted.
```bash
./safemove.sh path/to/infile path/to/outfile
```

---

## Testing & Cleaning

### Run Test Suite
Execute the testing framework to validate error handling (e.g., system call faults) and functionality:
```bash
make test
```

### Clean Build Artifacts
Remove compiled binaries, shared libraries, and generated test files:
```bash
make clean
```
