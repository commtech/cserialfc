# Connect

###### Code Support
| Code | Version |
| ---- | ------- |
| serialfc-windows | 2.0.0 |
| serialfc-linux | 2.0.0 |
| cserialfc | 1.0.0 |


## Connect
```c
int serialfc_connect(unsigned port_num, serialfc_handle *h)
```

| Parameter     | Type           | Description
| ------------ | --------------- | --------------------------------------------
| `port_num`    | `unsigned`      | The port number you would like to connect to
| `h`          | `serialfc_handle *` | The handle to your port

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SERIALFC_INVALID_ACCESS` | 17002 | Insufficient permissions |
| `SERIALFC_PORT_NOT_FOUND` | 17003 | Port not found |

###### Examples
Connect to port 3.
```c
#include <Windows.h>
...

serialfc_handle h;

serialfc_connect(3, &h);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
