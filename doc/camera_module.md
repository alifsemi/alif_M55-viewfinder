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
    /* Enable camera sensor clock.
       Initialize I2C communication to camera.
       Reset and configure the camera module.
       Check camera ID. */
}

int32_t CAM123_Start(void)
{
    /* Implement camera streaming start */
}

int32_t CAM123_Stop(void)
{
    /* Implement camera streaming stop */
}

int32_t CAM123_Control(uint32_t control, uint32_t arg)
{
    /* The following controls can be implemented:
    CPI_CAMERA_SENSOR_CONFIGURE
    CPI_CAMERA_SENSOR_GAIN
    See also Driver_CPI.h
    */
}

int32_t CAM123_Uninit(void)
{
    /* Disable camera sensor clock */
}
```

Then provide the needed CSI configuration information and register the sensor with the CAMERA_SENSOR macro.
In the CSI_INFO struct you need to define the used MIPI CSI clock frequency, data type and virtual channel identifier.

Note that it is possible to override the CPI block color mode, how the data is written to the camera_buffer by the CPI when calling CaptureFrame(camera_buffer);
See table cpi_data_mode_settings in Driver_MIPI_CSI2.c
For more details see the [datasheets](https://alifsemi.com/support/datasheets/ensemble).
And Camera Interfaces in [Hardware reference manual](https://alifsemi.com/support/reference-manuals).

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

Adjust the sizes of camera_buffer and image_buffer in viewfinder main.c according to camera resolution and format.

Note that viewfinder example does 8-bit Bayer conversion by default and you may need to adapt or skip the routine depending on your camera output format.
