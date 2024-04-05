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

For a new camera module "CAM123" you need to implement the Init(), Uninit(), Start(), Stop() and Control() routines
```
int32_t CAM123_Init(void)
{
}

int32_t CAM123_Start(void)
{
}

int32_t CAM123_Stop(void)
{
}

int32_t CAM123_Control(uint32_t control, uint32_t arg)
{
}

int32_t CAM123_Uninit(void)
{
}
```

Then provide the needed CSI configuration information and register the sensor with the CAMERA_SENSOR macro.

```
/**
\brief CAM123 Camera Sensor CSi informations
\ref CSI_INFO
*/
static CSI_INFO CAM123_csi_info =
{
    .frequency                = CAM123_CAMERA_SENSOR_CSI_FREQ,
    .dt                       = CAM123_CAMERA_SENSOR_CSI_DATA_TYPE,
    .n_lanes                  = CAM123_CAMERA_SENSOR_CSI_N_LANES,
    .vc_id                    = CAM123_CAMERA_SENSOR_CSI_VC_ID,
    .cpi_cfg.override         = CAM123_CAMERA_SENSOR_OVERRIDE_CPI_COLOR_MODE,
    .cpi_cfg.cpi_color_mode   = CAM123_CAMERA_SENSOR_CPI_COLOR_MODE
};

/**
\brief CAM123 Camera Sensor Operations
\ref CAMERA_SENSOR_OPERATIONS
*/
static CAMERA_SENSOR_OPERATIONS CAM123_ops =
{
    .Init    = CAM123_Init,
    .Uninit  = CAM123_Uninit,
    .Start   = CAM123_Start,
    .Stop    = CAM123_Stop,
    .Control = CAM123_Control,
};

/**
\brief CAM123 Camera Sensor Device Structure
\ref CAMERA_SENSOR_DEVICE
*/
static CAMERA_SENSOR_DEVICE CAM123_camera_sensor =
{
    .width    = CAM123_CAMERA_SENSOR_FRAME_WIDTH,
    .height   = CAM123_CAMERA_SENSOR_FRAME_HEIGHT,
    .csi_info = &CAM123_csi_info,
    .ops      = &CAM123_ops,
};

/* Registering CPI sensor */
CAMERA_SENSOR(CAM123_camera_sensor)
```
