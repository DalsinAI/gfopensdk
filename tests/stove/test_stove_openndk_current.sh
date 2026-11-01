#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Brings the stoves' OpenNDK up to date, then checks it is. The 68k stoves
# read OpenNDK through a link to the checkout amigachrome's
# scripts/stove_openndk.py made (~/AmigaChrome/stoves/openndk); this does
# what its "fetch" does (git pull --ff-only there, nothing else), so Cradle's
# repo_test can keep the stoves current. Exits 1 if the checkout can't be
# brought to origin's main.
set -u
CHECKOUT=${OPENNDK_CHECKOUT:-"$HOME/AmigaChrome/stoves/openndk"}
[ -d "$CHECKOUT/.git" ] || { echo "no OpenNDK checkout at $CHECKOUT"; exit 1; }
before=$(git -C "$CHECKOUT" rev-parse HEAD)
git -C "$CHECKOUT" pull -q --ff-only || { echo "git pull --ff-only failed in $CHECKOUT"; exit 1; }
after=$(git -C "$CHECKOUT" rev-parse HEAD)
remote=$(git -C "$CHECKOUT" rev-parse origin/main)
echo "$CHECKOUT: $before -> $after ($(git -C "$CHECKOUT" log --oneline -1))"
[ "$after" = "$remote" ] || { echo "not at origin/main ($remote)"; exit 1; }
echo "the stoves' OpenNDK is current"
