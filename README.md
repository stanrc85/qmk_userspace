# QMK Userspace

An [external QMK userspace][external-userspace] for maintaining my own keymaps and configuration files outside the main firmware repository.

## Local Compiling

Compile the firmware for a particular keyboard and keymap:

```shell
qmk compile -kb <keyboard> -km <keymap>
```

Compile all build targets, as defined in [`qmk.json`](./qmk.json):
```shell
qmk userspace-compile
```

## Management

Create a new keymap and add it to the build targets file:

```shell
qmk userspace-add -kb <your_keyboard> -km <your_keymap>
```

Remove a keymap:

```shell
qmk userspace-remove -kb <your_keyboard> -km <your_keymap>
```

## Github Actions

Modify `.github/workflows/build_binaries.yml` to use VIAL repo.

```shell
    with:
      qmk_repo: vial-kb/vial-qmk
      qmk_ref: vial
```
New builds will be compiled when changes are made to this repo.
