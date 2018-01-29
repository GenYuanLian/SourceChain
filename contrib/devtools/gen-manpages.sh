#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SRCCHAIND=${SRCCHAIND:-$SRCDIR/srcchaind}
SRCCHAINCLI=${SRCCHAINCLI:-$SRCDIR/srcchain-cli}
SRCCHAINTX=${SRCCHAINTX:-$SRCDIR/srcchain-tx}
SRCCHAINQT=${SRCCHAINQT:-$SRCDIR/qt/srcchain-qt}

[ ! -x $SRCCHAIND ] && echo "$SRCCHAIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
STKVER=($($SRCCHAINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for srcchaind if --version-string is not set,
# but has different outcomes for srcchain-qt and srcchain-cli.
echo "[COPYRIGHT]" > footer.h2m
$SRCCHAIND --version | sed -n '1!p' >> footer.h2m

for cmd in $SRCCHAIND $SRCCHAINCLI $SRCCHAINTX $SRCCHAINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${STKVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${STKVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
