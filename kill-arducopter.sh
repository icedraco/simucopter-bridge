#!/bin/bash

ps -ef | grep copter | grep -v grep | awk '{print $2}' | xargs kill -9

