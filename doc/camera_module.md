# Camera module driver howto

In viewfinder demo project, first comment out the default camera component in cproject.yaml

```
# - component: AlifSemiconductor::BSP:External peripherals:CAMERA Sensor ARX3A0
```

There are multiple camera module examples in Alif Ensemble CMSIS pack.
See folder **components/Source** for reference.

```
MT9M114_Camera_Sensor.c
ar0144_camera_sensor.c
arx3A0_camera_sensor.c
```
