# tcount : A very simple, stupid timer/counter for linux terminal.

### Dependencies :
* canberra-gtk-play (libcanberra)
* figlet

### Building :
```sh
git clone https://github.com/ahmad-alsaidy/tcount.git
cd build
./build.sh
```

### Usage :
* `tcount` : to play counter (count up)
* `tcount '$h $m $s'` : to play timer (count down). Replace `$` with any number. You have to add single quotes and specify [h, m, s].

### Examples :
* `tcount '0h 0m 10s'` : play timer for 10 seconds.
* `tcount '0h 30m 0s'` : play timer for 30 minutes.
* `tcount '1h 0m 0s'` : play timer for 1 hour.
