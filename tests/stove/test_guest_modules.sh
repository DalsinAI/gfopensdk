#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Builds every amicradle-guest module (each build-amiga.sh) twice with the
# os32-gcc16 stove: once against the vendor NDK the stove kept
# (ndk-include.vendor) and once against this checkout's OpenNDK, and lists
# each module that builds with the first but not the second, with its first
# errors. The live stove is not changed: each pass runs through a stove of
# links whose compilers put the chosen include folder first.
#   GUEST=/path/to/amicradle-guest  (default: Cradle's checkout, its HEAD)
#   ONLY="libraries/opendos devices/opentimer.device"  (default: every module)
#   JOBS=3  (modules built at once; 3 is Daletop's limit for builds)
# Exits 1 if a module builds with the vendor NDK and not with OpenNDK.
set -u
HERE=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
REAL=${STOVE:-"$HOME/AmigaChrome/stoves/os32-gcc16"}
SRC=${GUEST:-"${AMIGACHROME_DEV:-$HOME/AmigaChrome-dev}/cradle-builds/DalsinAI__amicradle-guest"}
JOBS=${JOBS:-3}
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

fake_stove() { # $1 name, $2 include folder, $3 a folder searched last (optional)
    s="$tmp/stove-$1"
    # a tree of links (not one link per folder), so that the scripts'
    # find "$P" -name ... still finds the .fd files
    mkdir -p "$s"
    cp -as "$REAL/prefix" "$s/prefix" || exit 2
    rm -rf "$s/prefix/bin"; mkdir -p "$s/prefix/bin"
    for b in "$REAL/prefix/bin"/*; do
        n=$(basename "$b")
        case $n in
        *-gcc|*-g++|*-c++|*-cpp)
            # after the build's own flags, so a script's -isystem comes
            # first, as it does on a stove whose NDK folder is switched
            if [ -n "${3:-}" ]; then
                printf '#!/bin/sh\nexec "%s" "$@" -isystem "%s" -idirafter "%s"\n' "$b" "$2" "$3"
            else
                printf '#!/bin/sh\nexec "%s" "$@" -isystem "%s"\n' "$b" "$2"
            fi > "$s/prefix/bin/$n"
            chmod +x "$s/prefix/bin/$n" ;;
        *) ln -s "$b" "$s/prefix/bin/$n" ;;
        esac
    done
}
# The third-party network SDK headers (Roadshow's bsdsocket and the AmiTCP
# ones) the vendor folder carried and OpenNDK has no file for: the stove
# keeps them reachable in its include folder (amicradle's
# scripts/stove_openndk.py), and so does this run, after everything else.
VENDOR="$REAL/prefix/m68k-amigaos/ndk-include.vendor"
extras="$tmp/extras"
(cd "$VENDOR" && find . -type f -name '*.h' | sed 's|^\./||') | while read -r f; do
    [ -e "$HERE/OpenNDK/Include_H/$f" ] && continue
    case $f in
    amitcp/*|arpa/*|bsdsocket/*|net/*|netinet/*|sys/*|netdb.h|pwd.h|resolv.h|syslog.h|utmp.h) ;;
    *) head -15 "$VENDOR/$f" | grep -qi roadshow || continue ;;
    esac
    mkdir -p "$extras/$(dirname "$f")"; ln -s "$VENDOR/$f" "$extras/$f"
done
fake_stove vendor "$VENDOR"
fake_stove openndk "$HERE/OpenNDK/Include_H" "$extras"
[ -d "$REAL/prefix/m68k-amigaos/ndk-include.vendor" ] || { echo "no vendor NDK kept in $REAL"; exit 2; }

for m in vendor openndk; do
    git -c advice.detachedHead=false clone -q --shared "$SRC" "$tmp/guest-$m" || exit 2
done
echo "guest at $(git -C "$tmp/guest-vendor" log --oneline -1), OpenNDK at $(git -C "$HERE" log --oneline -1)"
if [ -n "${ONLY:-}" ]; then targets=$ONLY; else
    targets=$(cd "$tmp/guest-vendor" && find . -name build-amiga.sh -not -path './.git/*' | sed 's|^\./||;s|/build-amiga.sh$||' | sort)
fi
mkdir -p "$tmp/log"
for m in vendor openndk; do
    for t in $targets; do echo "$m $t"; done
done > "$tmp/list"
cat > "$tmp/one.sh" <<SH
#!/bin/sh
m=\$1; t=\$2; k=\$(echo "\$m-\$t" | tr / _)
cd "$tmp/guest-\$m/\$t" || exit 0
if PATH="$tmp/stove-\$m/prefix/bin:\$PATH" STOVE="$tmp/stove-\$m" OUT="$tmp/out/\$k" timeout 600 sh ./build-amiga.sh > "$tmp/log/\$k" 2>&1; then echo ok > "$tmp/log/\$k.rc"; else echo fail > "$tmp/log/\$k.rc"; fi
SH
xargs -P "$JOBS" -L 1 sh "$tmp/one.sh" < "$tmp/list"

bad=0; both=0; good=0; vend=""
for t in $targets; do
    k=$(echo "$t" | tr / _)
    v=$(cat "$tmp/log/vendor-$k.rc" 2>/dev/null || echo none)
    o=$(cat "$tmp/log/openndk-$k.rc" 2>/dev/null || echo none)
    if [ "$o" = ok ]; then good=$((good+1)); [ "$v" = ok ] || vend="$vend $t"
    elif [ "$v" = ok ]; then
        bad=$((bad+1)); echo "== $t: builds with the vendor NDK, not with OpenNDK"
        grep -m 12 -E 'error|undefined reference|In file included|fatal' "$tmp/log/openndk-$k" | sed "s|$tmp/guest-openndk/||g;s|$HERE/||g"
    else both=$((both+1)); echo "-- $t: fails with both:"; { grep -m 3 -E 'error|undefined|fatal|not' "$tmp/log/vendor-$k" || tail -n 3 "$tmp/log/vendor-$k"; } | sed "s|$tmp/guest-vendor/||g"
    fi
done
[ -z "$vend" ] || echo "builds with OpenNDK only:$vend"
echo "summary: $good build with OpenNDK, $bad only with the vendor NDK, $both with neither"
[ $bad -eq 0 ]
