import re

from typing import Optional, Tuple

class Cube:
  def __init__(self, x: Tuple[int, int], y: Tuple[int, int], z: Tuple[int, int], on: bool) -> None:
    self.min_x, self.max_x = min(x), max(x)
    self.min_y, self.max_y = min(y), max(y)
    self.min_z, self.max_z = min(z), max(z)
    self.on = on

    self.volume = (self.max_x - self.min_x + 1) * (self.max_y - self.min_y + 1) * (self.max_z - self.min_z + 1)

  def __str__(self) -> str:
    return f'{"on" if self.on else "off"} x={self.min_x}..{self.max_x} y={self.min_y}..{self.max_y} z={self.min_z}..{self.max_z}'

  def is_small(self) -> bool:
    return -50 <= min(self.min_x, self.min_y, self.min_z) and 50 >= max(self.max_x, self.max_y, self.max_z)

  def intersect(self, other: 'Cube') -> Optional['Cube']:
    if self.max_x < other.min_x or self.min_x > other.max_x:
      return None
    if self.max_y < other.min_y or self.min_y > other.max_y:
      return None
    if self.max_z < other.min_z or self.min_z > other.max_z:
      return None

    return Cube(
        (min(self.max_x, other.max_x), max(self.min_x, other.min_x)),
        (min(self.max_y, other.max_y), max(self.min_y, other.min_y)),
        (min(self.max_z, other.max_z), max(self.min_z, other.min_z)),
        other.on if self.on != other.on else not other.on)


class Reactor:
  def __init__(self) -> None:
    self.regions = []

  def __str__(self) -> str:
    return "\n".join(str(x) for x in self.regions)

  def add_region(self, region: Cube) -> None:
    self.regions.append(region)

  def reboot(self, small: bool = False) -> int:
    processed = []

    for i, region in enumerate(self.regions):
      if small and not region.is_small():
        continue

      next_processed = []

      for previous in processed:
        next_processed.append(previous)
        if overlap := previous.intersect(region):
          next_processed.append(overlap)

      if region.on:
        next_processed.append(region)

      processed = next_processed

    return sum(region.volume if region.on else -region.volume for region in processed)


def read_input() -> Reactor:
  reactor = Reactor()

  with open('input.txt') as file:
    for line in file.readlines():
      m = re.match(r'^(on|off) x=(-?\d+)\.\.(-?\d+),y=(-?\d+)\.\.(-?\d+),z=(-?\d+)\.\.(-?\d+)', line.strip())
      status, min_x, max_x, min_y, max_y, min_z, max_z = m.groups()
      reactor.add_region(Cube((int(min_x), int(max_x)), (int(min_y), int(max_y)), (int(min_z), int(max_z)), status == "on"))

  return reactor


def run() -> None:
  reactor = read_input()
  print(f'Initial reboot, active cubes: {reactor.reboot(True)}')
  print(f'Full reboot, active cubes: {reactor.reboot()}')


run()