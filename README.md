
### Prereqs

```bash
sudo apt install make cmake g++ libstdc++6 libreadline-dev pip
pip install conan
```

### Building

#### First-time setup

```bash
# Install deps
conan install .

# first-time config
cmake .

# after that:
make -j
```

### Emacs Setup

1. Generate JSON compilation database

   ```bash
   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .
   ```

1. Build and install `rtags` locally and add `rdm` to `$PATH` from source at https://github.com/Andersbakken/rtags. I
   think you may need to install `libclang-dev` as well (TODO: verify)

1. Install `clangd`

   ```bash
   sudo apt install clangd
   ```
