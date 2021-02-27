#!/usr/bin/env python3

# WS server example

import asyncio
import websockets
import time
import os

from select import poll, POLLPRI

async def button_thread(websocket, path):
    name = await websocket.recv()
    print(f"< {name}")

    greeting = f"Hello {name}!"
    await websocket.send(greeting)

    button_fd = os.open("/sys/class/gpio/gpio9/value", os.O_RDONLY)
    p = poll()
    p.register(button_fd, POLLPRI)

    pollCount = 0
    
    while True :
        events = p.poll(100)
        for e in events:
            os.lseek(button_fd, 0, os.SEEK_SET)
            button_value = os.read(button_fd, 1)
            await websocket.send(button_value.decode("utf-8"))
            print(f"> {button_value}")

        pollCount += 1
        if (pollCount % 10) == 0:
            try:
                await websocket.send("check connection")
            except Exception as e:
                print(e)
                break

start_server = websockets.serve(button_thread, "192.168.3.8", 5678)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
