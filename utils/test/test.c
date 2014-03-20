#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
int _getch(void);
#endif

#include <serialfc.h>

#define DATA_LENGTH 20
#define NUM_ITERATIONS 100

int init(serialfc_handle h);
int loop(serialfc_handle h);

int main(int argc, char *argv[])
{
    serialfc_handle h;
    int e = 0;
    unsigned port_num;
    unsigned i = 0;

    if (argc != 2) {
        fprintf(stdout, "%s PORT_NUM\n", argv[0]);
        return EXIT_FAILURE;
    }

    port_num = atoi(argv[1]);

    e = serialfc_connect(port_num, &h);
    if (e != 0) {
        fprintf(stderr, "serialfc_connect failed with %d\n", e);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "This is a very simple test to verify your card is\n");
    fprintf(stdout, "communicating correctly.\n\n");

    fprintf(stdout, "NOTE: This will change your settings to defaults.\n\n");

    fprintf(stdout, "1) Connect your loopback plug.\n");
    fprintf(stdout, "2) Press any key to start the test.\n\n");


    _getch();

    e = init(h);
    if (e != 0) {
        serialfc_disconnect(h);
        return EXIT_FAILURE;
    }

    for (i = 0; i < NUM_ITERATIONS; i++) {
        e = loop(h);
        if (e != 0) {
            if (e == -1) {
                break;
            }
            else {
                serialfc_disconnect(h);
                return EXIT_FAILURE;
            }
        }
    }

    if (e != -1)
        fprintf(stdout, "Passed, you can begin development.\n");
    else
        fprintf(stderr, "Failed, contact technical support.\n");

    serialfc_disconnect(h);

    return EXIT_SUCCESS;
}

int init(serialfc_handle h)
{
#ifdef _WIN32
    DCB mdcb;
    COMMTIMEOUTS cto;
#else
    struct termios tios;
#endif
    unsigned type = 0;
    int e = 0;

    e = serialfc_set_clock_rate(h, 18432000);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_set_clock_rate failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_set_sample_rate(h, 16);
    if (e != 0) {
        fprintf(stderr, "serialfc_set_sample_rate failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_disable_rs485(h);
    if (e != 0) {
        fprintf(stderr, "serialfc_connect failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_disable_echo_cancel(h);
    if (e != 0) {
        fprintf(stderr, "serialfc_disable_echo_cancel failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_enable_termination(h);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_enable_termination failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_set_tx_trigger(h, 32);
    if (e != 0) {
        fprintf(stderr, "serialfc_set_tx_trigger failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_set_rx_trigger(h, 32);
    if (e != 0) {
        fprintf(stderr, "serialfc_set_rx_trigger failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_disable_isochronous(h);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_disable_isochronous failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_disable_external_transmit(h);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_disable_external_transmit failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_set_frame_length(h, 1);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_set_frame_length failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_disable_9bit(h);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_disable_9bit failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_disable_fixed_baud_rate(h);
    if (e != 0 && e != SERIALFC_NOT_SUPPORTED) {
        fprintf(stderr, "serialfc_disable_fixed_baud_rate failed with %d\n", e);
        return EXIT_FAILURE;
    }

#ifdef _WIN32
    memset(&mdcb, 0, sizeof(mdcb));
    memset(&cto, 0, sizeof(cto));

    if (BuildCommDCB("baud=115200 parity=N data=8 stop=1", &mdcb) == 0) {
        fprintf(stdout, "BuildCommDCB failed with %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    cto.ReadIntervalTimeout = 1;

    if (SetCommState(h, &mdcb) == FALSE) {
        fprintf (stderr, "SetCommState failed with %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    if (SetCommTimeouts(h, &cto) == FALSE) {
        fprintf(stdout, "SetCommTimeouts failed with %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    PurgeComm(h, PURGE_TXCLEAR | PURGE_RXCLEAR);
#else
    ioctl(h, IOCTL_FASTCOM_GET_CARD_TYPE, &type);

    if (type == SERIALFC_CARD_TYPE_PCIE) {
        int mode = 0;

        ioctl(h, TIOCMGET, &mode);
        mode &= ~TIOCM_DTR; /* Set DTR to 1 (transmitter always on, 422) */
        ioctl(h, TIOCMSET, &mode);
    }

    tcgetattr(h, &tios);

    tios.c_iflag = IGNBRK;
    tios.c_oflag = 0;
    tios.c_cflag = CS8 | CREAD | CLOCAL;
    tios.c_lflag &= (~ICANON | ISIG | ECHO);

    cfsetospeed(&tios, B115200);
    cfsetispeed(&tios, 0); /* Set ispeed = ospeed */

    tcsetattr(h, TCSANOW, &tios);
#endif

    return EXIT_SUCCESS;
}

int loop(serialfc_handle h)
{
    unsigned bytes_written = 0, bytes_read = 0;
    char odata[DATA_LENGTH];
    char idata[100];
    int e = 0;

    memset(&odata, 0x01, sizeof(odata));
    memset(&idata, 0x00, sizeof(idata));

    e = serialfc_write_with_blocking(h, odata, sizeof(odata), &bytes_written);
    if (e != 0) {
        fprintf(stderr, "serialfc_write failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = serialfc_read_with_blocking(h, idata, sizeof(idata), &bytes_read);
    if (e != 0) {
        fprintf(stderr, "serialfc_read with %d\n", e);
        return EXIT_FAILURE;
    }

    if (bytes_read == 0 || memcmp(odata, idata, sizeof(odata)) != 0)
        return -1;

    return EXIT_SUCCESS;
}

#ifndef _WIN32
/* reads from keypress, doesn't echo */
int _getch(void)
{
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif
