# Makiyu's Dotfiles

wip... buuttt I'll give you a short tour

## Makiyu's Personal Dotfile Manager

I got frustrated on which dotfile manager I should use so I made my own with my non-existant C++ skills (would not recommend to use since... this is my first C++ program)

### Installation


```
$ g++ -std=c++11 mpdfm.cpp -o mpdfm
```

### Commands

#### `./mpdfm dot <target_path> [new_path_in_dotfiles_dir]`

Moves a file to this current directory and makes a symlink back to the target path.

__Example:__
```
$ ./mpdfm dot ~/.gitconfig
/User/Makiyu/.gitconfig -> /User/Makiyu/dotfiles/.gitconfig
Moved /User/Makiyu/.gitconfig to /User/Makiyu/dotfiles/.gitconfig
Added a symlink to /User/Makiyu/.gitconfig from /User/Makiyu/dotfiles/.gitconfig
```

### `./mpdfm link <file_or_dir_in_repo> [target_to_link]`

Makes a symlink of a file or directory in this repository to the current machine.

__Example:__
```
$ ./mpdfm link .vimrc
Added a symlink to /Users/Makiyu/.vimrc from /Users/Makiyu/dotfiles/.vimrc
```

## License

give me a few days to think about it
