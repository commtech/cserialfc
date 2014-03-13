# Disconnect


###### Code Support
| Code | Version |
| ---- | -------- |
| serialfc-windows | 2.0.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |


## Disconnect
```c
int serialfc_disconnect(serialfc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `serialfc_handle` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |


###### Examples
```c
#include <serialfc.h>
...

serialfc_disconnect(h);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
