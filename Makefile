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
	dungeon.s \
	update.s \
	player.s \
	monster.s

OBJS = $(NAME).o \
	crt0.o \
	attract_monsters.o \
	attract_scores.o \
	utils.o \
	dungeon.o \
	update.o \
	player.o \
	monster.o

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

dungeon.o: dungeon.s
	$(CA65) dungeon.s

dungeon.s: dungeon.c
	$(CC65) -Oi dungeon.c --add-source

update.o: update.s
	$(CA65) update.s

update.s: update.c
	$(CC65) -Oi update.c --add-source

player.o: player.s
	$(CA65) player.s

player.s: player.c
	$(CC65) -Oi player.c --add-source

monster.o: monster.s
	$(CA65) monster.s

monster.s: monster.c
	$(CC65) -Oi monster.c --add-source

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
