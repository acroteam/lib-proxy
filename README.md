# lib-proxy

This is 'library proxy' project.


# Formatting

This file will be primarily viewed in primitive Linux text console.
Rendering in browser is secondary.


# Task overview

We have two almost independent pieces of code executing independent tasks
but using services of each other. Currently all code is executed in
single process. We need to split code into two separate processes to
isolate tasks from each other. At the same time we need to implement some
cross process communication mechanism to preserve ability for tasks to
use services of each other.


# Transport for cross process communication

Initially 'transport' will be based on unix stream sockets. Howerver low
level transport must be replaceable. Possible alternative can be based on
tcp stream sockets if we will need to split our tasks between independent
computers.


# Client and Server

Both unix and tcp stream sockets assume separation of 'client' and
'server' roles. Both our tasks are almost equal. Each task acts both as
server and as client. We may deliberately assign client and server roles.
Alternatively we can establish two independent communication channels
with each task acting as server on one channel and as client on another
channel.
