#!/bin/sh
# nschk.sh - list C functions in the current directory that are missing a namespace prefix
#
# usage: nscheck.sh <prefix>        e.g.  nscheck.sh env   (checks for env_)
#
# Checks *.h declarations and non-static *.c definitions (top-level lines only).
# static functions and typedefs are ignored. Exit status: 0 = clean, 1 = violations, 2 = usage.

if [ $# -ne 1 ]; then
    echo "usage: $0 <prefix>" >&2
    exit 2
fi

NS="$1"
case "$NS" in
    *_) ;;
    *)  NS="${NS}_" ;;
esac

FILES=$(ls *.h *.c 2>/dev/null)
if [ -z "$FILES" ]; then
    echo "nscheck: no .h or .c files in $(pwd)" >&2
    exit 2
fi

BAD=$(grep -n "^[a-z].*(" $FILES \
    | grep -v ":static " \
    | grep -v ":typedef " \
    | grep -v "[ *]${NS}[a-zA-Z0-9_]*(")

if [ -n "$BAD" ]; then
    echo "$BAD"
    echo "nscheck: functions above are missing the '${NS}' prefix" >&2
    exit 1
fi

echo "nscheck: all functions prefixed '${NS}'"
exit 0
