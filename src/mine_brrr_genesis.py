#!/usr/bin/env python3
import time, struct, hashlib, scrypt

# ---------- EDIT ME ----------
psz_timestamp = "May 2025 – BrrrFren brings the chill 🧊".encode("utf-8")
pubkey_hex    = "02b720d7bccf7f6d2d855e161ad598a3b13c9cfa6b1f059a3bad960fa34f5e01ad"
premine_value = 3570000                       # whole coins

# nBits         = 0x207fffff
# nTime         = 1747693169                    # keep or bump

# For testnet
# nBits = 0x1e0ffff0
# nTime = 1747689314

# For regtest
nBits = 0x207fffff
nTime = 1747689314

# ------------------------------

target = (nBits & 0xffffff) * 2**(8*((nBits >> 24) - 3))

def little(x, length):          # int→little-endian bytes
    return x.to_bytes(length, 'little')

def dbl_sha256(b):              # Bitcoin-style header hash
    return hashlib.sha256(hashlib.sha256(b).digest()).digest()

def scrypt_hash(header):
    return scrypt.hash(header, header, 1024, 1, 1, 32)[::-1]  # big-endian

# Build the (single) coinbase tx ------------------------------------------------
script_pub = bytes.fromhex("21" + pubkey_hex + "ac")
coinbase   = (
    little(1,4) +                     # version
    b'\x01' +                         # 1 input
    b'\x00'*32 + little(0xffffffff,4) # prevout
    + bytes([len(psz_timestamp)]) + psz_timestamp
    + b'\xff\xff\xff\xff'             # sequence
    + b'\x01'                         # 1 output
    + little(premine_value*10**8,8)   # 8-byte value (satoshi)
    + bytes([len(script_pub)]) + script_pub
    + little(0,4))                    # locktime

merkle_root = dbl_sha256(coinbase)

print("Mining …")
nonce = 0
start = time.time()
while True:
    header = (
        little(1,4) +                 # version
        b'\x00'*32 +                  # prev block
        merkle_root +                 # merkle root
        little(nTime,4) +
        little(nBits,4) +
        little(nonce,4))
    h = int.from_bytes(scrypt_hash(header), 'big')
    if h < target:
        print(f"Found in {time.time()-start:.1f}s  nonce={nonce}")
        print("hash  =", scrypt_hash(header).hex())
        print("mrkl  =", merkle_root[::-1].hex())
        break
    nonce += 1

