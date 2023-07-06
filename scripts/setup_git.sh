#!/bin/sh
git config --global user.name raghugoud@nyu.edu
git config --global --list

ssh-keygen -t ed25519 -C raghugoud@nyu.edu
cat ~/.ssh/id_ed25519.pub
echo "add this to github ssh-key"

#change remote url to use ssh authentication

git remote set-url orgin git@github.com:raghu467/LDD_workspace.git
