
Original: [https://dwm.suckless.org/](https://dwm.suckless.org/)

This project based on dwm 6.4

See also: [https://github.com/psqq/dwm-scripts](https://github.com/psqq/dwm-scripts)

# build and install

Build and install `dwm`:

```bash
cd ~
git clone https://github.com/psqq/dwm
cd dwm
make build
make install
```

Get `dwm-scripts`:

```bash
cd ~
git clone https://github.com/psqq/dwm-scripts
chmod +x ~/dwm-scripts/startdwm
chmod +x ~/dwm-scripts/dwm-logs.sh
```

Copy `src/config.example.h` to `src/config.h` and change `DWM_SCRIPTS_DIR`.

Add to `.xinitrc`:

```bash
~/dwm-scripts/dwm-logs.sh
python ~/dwm-scripts/status_bar.py loop &
exec ~/dwm-scripts/startdwm

```

# Running with restart and logs support

`~/dwm-scripts/startdwm`:

```bash
#!/bin/bash

ssh-agent dwm 1>>~/.dwm.log 2>>~/.dwm.error.log
```

`.xinitrc`:

```bash
exec ~/dwm-scripts/startdwm
```

# lsp

`clangd` used for lsp.

# todo

- [ ] перенести весь код на C++

# bugs

- [ ] когда открыто модальное/плавающее окно не перемещать фокус на движение мыши (copyq)
  - [ ] добавить также хоткей, который обратно перемещает фокус на горячую клавишу
- [ ] окно в фулскрине не перемещается на другой монитор
