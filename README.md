# QMK Userspace

An external QMK userspace for maintaining my own VIAL keymaps and configuration files outside the main firmware repository.

## Local Compiling

Compile the firmware for a particular keyboard and keymap (within VIAL firmeware repo):

```shell
cd vial-qmk
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

# Board Specific Notes

## KBDFans Maja v2
- Very tight space contraints, check `rules.mk` and `config.h` for enabled and disabled features. Most RGB lighting modes are disabled, enable only the ones that will be used.
- QMK Settings and Tap Dance enabled.

## Noxary Valhalla v2
- QMK Settings and Tap Dance enabled.

## Sneakbox AlicecloneRGB
- QMK Settings and Tap Dance enabled.
- Used across multiple PCBs: Aliceclonergb, M4, M5.
- Indicator LEDs blink on start up.
- Indicator LEDs configured for CAPS LOCK and layer indicators.
- RGB timeout when keyboard is idle.

## Smith and Rune Iron Alice
- QMK Settings and Tap Dance enabled.
- Keyboard source code manually added to personal VIAL repo.

## Neo Ergo
- QMK Settings and Tap Dance enabled.
- Keyboard source code manually added to personal VIAL repo.
