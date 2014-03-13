# 9-Bit Protocol

Enabling 9-Bit protocol has a couple of effects.

- Transmitting with 9-bit protocol enabled automatically sets the 1st byte's 9th bit to MARK, and all remaining bytes's 9th bits to SPACE.
- Receiving with 9-bit protocol enabled will return two bytes per each 9-bits of data. The second of each byte-duo contains the 9th bit.

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.2.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |

###### Card Support
| Card Family | Supported |
| ----------- |:-----:|
| FSCC (16C950) | Yes |
| Async-335 (17D15X) | No |
| Async-PCIe (17V35X) | No |


## Get
```c
int serialfc_get_9bit(serialfc_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current 9-Bit value |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

unsigned status;

serialfc_get_9bit(h, &status);
```


## Enable
```c
int serialfc_enable_9bit(serialfc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

serialfc_enable_9bit(h);
```


## Disable
```c
int serialfc_disable_9bit(serialfc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_NOT_SUPPORTED` | 17000 | Not supported on this family of cards |

###### Examples
```c
#include <serialfc.h>
...

serialfc_disable_9bit(h);
```


### Additional Resources
- Complete example: [`examples/nine-bit.c`](../examples/nine-bit.c)
