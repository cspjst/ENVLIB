#!/bin/sh
# Transfer a satisfactory build: bin/ENV.lib -> lib/, src/ENV/*.h -> include/ENV/
set -e
cd "$(dirname "$0")"

LIB=bin/ENV.lib

if [ ! -f "$LIB" ]; then
    echo "transfer: $LIB not found - build first (./cmk.sh && ./bld.sh in src)" >&2
    exit 1
fi

mkdir -p lib include/ENV

cp "$LIB" lib/

# clear old headers so ones deleted from src/ENV don't linger
rm -f include/ENV/*.h
cp src/ENV/*.h include/ENV/

echo "transferred: lib/ENV.lib + $(ls include/ENV/*.h | wc -l | tr -d ' ') headers -> include/ENV/"
