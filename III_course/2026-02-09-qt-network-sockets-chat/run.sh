#!/usr/bin/env bash
set -euo pipefail

BASE="/home/tysser/Scripts/jetbrains/cpp_course/cmake-build-debug/III_course/2026-02-09-qt-network-sockets-chat"
SERVER="$BASE/server/chat_server"
CLIENT="$BASE/client/chat_client"

"$SERVER" &
server_pid=$!

sleep 0.5

"$CLIENT" &
"$CLIENT" &
"$CLIENT" &
"$CLIENT" &

wait $server_pid