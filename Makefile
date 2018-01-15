CC65 = cc65
CA65 = ca65
LD65 = ld65
NAME = wow
CFG = nes.cfg
LIB = runtime.lib

SRCS = $(NAME).s \
	attract_monsters.s \
	attract_scores.s \
	utils.s \
	run_dungeon.s

OBJS = $(NAME).o \
	crt0.o \
	attract_monsters.o \
	attract_scores.o \
	utils.o \
	run_dungeon.o

all: $(NAME).nes 

$(NAME).nes: $(OBJS) $(LIB) $(CFG)
	$(LD65) -C $(CFG) -o $(NAME).nes $(OBJS) $(LIB)
	@echo $(NAME).nes created

crt0.o: crt0.s
	$(CA65) crt0.s

attract_monsters.o: attract_monsters.s
	$(CA65) attract_monsters.s

attract_monsters.s: attract_monsters.c
	$(CC65) -Oi attract_monsters.c --add-source

attract_scores.o: attract_scores.s
	$(CA65) attract_scores.s

attract_scores.s: attract_scores.c
	$(CC65) -Oi attract_scores.c --add-source

utils.o: utils.s
	$(CA65) utils.s

utils.s: utils.c
	$(CC65) -Oi utils.c --add-source

run_dungeon.o: run_dungeon.s
	$(CA65) run_dungeon.s

run_dungeon.s: run_dungeon.c
	$(CC65) -Oi run_dungeon.c --add-source

$(NAME).o: $(NAME).s
	$(CA65) $(NAME).s

$(NAME).s: $(NAME).c
	$(CC65) -Oi $(NAME).c --add-source

clean:
	rm -f $(NAME).nes *.o $(SRCS)

xfer:   $(NAME).nes
	scp $(NAME).nes root@lakka:/storage/roms

run:	$(NAME).nes xfer
	ssh root@lakka "systemctl stop retroarch ; retroarch -L /tmp/cores/fceumm_libretro.so /storage/roms/$(NAME).nes ; systemctl start retroarch"
