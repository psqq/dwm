
# build and install

```bash
make build
sudo make install

```

# Running with restart and logs support

`~/scripts/startdwm`:

```bash
#!/bin/bash

ssh-agent dwm 1>>~/.dwm.log 2>>~/.dwm.error.log
```

`.xinitrc`:

```bash
exec ~/scripts/startdwm
```

# lsp

`clangd` used for lsp.

# todo

- [ ] перенести весь код на C++

# bugs

- [ ] когда открыто модальное/плавающее окно не перемещать фокус на движение мыши (copyq)
  - [ ] добавить также хоткей, который обратно перемещает фокус на горячую клавишу
- [ ] окно в фулскрине не перемещается на другой монитор
