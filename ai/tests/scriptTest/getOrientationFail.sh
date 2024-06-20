#!/bin/expect

if { $argc != 3 } {
    puts "Usage: $argv0 <server> <port> <team_name>"
    exit 1
}

set server [lindex $argv 0]
set port [lindex $argv 1]
set team_name [lindex $argv 2]

spawn nc $server $port

expect "WELCOME" { send "$team_name\r" }

expect "\n" { send "Broadcast OKOKOKOK\r" }
expect "ok" { send "Broadcast OKOKOKOK\r" }

send "\003"

expect eof
