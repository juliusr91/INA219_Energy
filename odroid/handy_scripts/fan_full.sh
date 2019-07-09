echo 0 | sudo tee /sys/devices/platform/pwm-fan/hwmon/hwmon0/automatic
echo 255 | sudo tee /sys/devices/platform/pwm-fan/hwmon/hwmon0/pwm1
