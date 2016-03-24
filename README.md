### Build manually
You can build tereZ from sources:
```bash
# Install build tools
sudo apt-get install build-essential cmake
# Install dependencies
sudo apt-get install libsdl2-dev libogg-dev libopenal-dev

# Let's make and run
mkdir ~/tmp && cd ~/tmp
hg clone https://qMBQx8GH@bitbucket.org/qMBQx8GH/terez
terez/tereZ/proj.cmake/run.sh

```
for g in $(seq 0 5 90); do convert tereZ/data/images/floor_tile.png -gravity NorthWest -background transparent -extent 200x120 -matte -virtual-pixel transparent -distort SRT "0,20 1.0,1.0 $g" left$g.png; done
for g in $(seq 0 5 90); do convert tereZ/data/images/floor_tile.png -gravity NorthWest -background transparent -extent 200x120 -flop -matte -virtual-pixel transparent -distort SRT "200,20 1.0,1.0 -$g" right$g.png; done
for g in $(seq 0 5 90); do composite left$g.png right$g.png "${g}sprite.png"; done
convert `ls *sprite.png|sort -g` +append door_open.png
convert `ls *sprite.png|sort -g -r` +append door_close.png



