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

To get started you can create a source file **app/camera_module.c** for your camera module and copy the base stucture from one of the existing camera drivers.

And add it to build in **cproject.yaml**

```
- file: app/camera_module.c
```

For a new camera module you need to provide the CSI configuration information and implement the Init(), Uninit(), Start(), Stop() and Control() routines and register the sensor with the CAMERA_SENSOR macro.
