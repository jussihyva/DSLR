#!/bin/bash

git submodule add git@github.com:jussihyva/libft.git lib/libft
git commit -m "Submodule (libft) added"

git rm --cached lib/libft # delete reference to submodule HEAD (no trailing slash)
git rm /home/juhani/DSLR/.gitmodules             # if you have more than one submodules,
                               # you need to edit this file instead of deleting!
rm -rf lib/libft/.git
rm -f lib/libft/.gitignore
rm -rf lib/libft/.vscode
rm -f lib/libft/author
git add lib/libft
git commit -m "Library (libft) added"

