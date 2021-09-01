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



git submodule add git@github.com:jussihyva/libft_addons.git lib/libft_addons
git commit -m "Submodule (libft_addons) added"

git rm --cached lib/libft_addons # delete reference to submodule HEAD (no trailing slash)
git rm /home/juhani/DSLR/.gitmodules             # if you have more than one submodules,
                               # you need to edit this file instead of deleting!
rm -rf lib/libft_addons/.git
rm -f lib/libft_addons/.gitignore
rm -rf lib/libft_addons/.vscode
rm -f lib/libft_addons/author
git add lib/libft_addons
git commit -m "Library (libft_addons) added"



git submodule add git@github.com:jussihyva/libft_addons.git lib/libft_printf
git commit -m "Submodule (libft_printf) added"

git rm --cached lib/libft_printf # delete reference to submodule HEAD (no trailing slash)
git rm /home/juhani/DSLR/.gitmodules             # if you have more than one submodules,
                               # you need to edit this file instead of deleting!
rm -rf lib/libft_printf/.git
rm -f lib/libft_printf/.gitignore
rm -rf lib/libft_printf/.vscode
rm -f lib/libft_printf/author
git add lib/libft_printf
git commit -m "Library (libft_printf) added"
