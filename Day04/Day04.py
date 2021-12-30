class Board:
    col_hits: list[int]
    row_hits: list[int]
    has_bingo: bool
    nums: dict[int, tuple[int, int]]
    def __init__(self, cells: list[list[int]]) -> None:
        width: int = len(cells[0])
        height: int = len(cells)
        self.col_hits = [height] * width
        self.row_hits = [width ] * height
        self.nums = dict()
        for y, row in enumerate(cells):
            for x, cell in enumerate(row):
                self.nums[cell] = (x, y)
        self.has_bingo = False
    def call(self, num: int) -> None:
        pos =  self.nums.pop(num, None)
        if pos is None: return
        x, y = pos
        self.col_hits[x] -= 1
        self.row_hits[y] -= 1
        self.has_bingo = (
            self.has_bingo or
            not self.col_hits[x] or
            not self.row_hits[y]
        )
    @property
    def unmarked_sum(self) -> int:
        return sum(self.nums.keys())
    @staticmethod
    def from_string(s: str) -> 'Board':
        print([[int(n) for n in l.split()] for l in s.split('\n')])
        return Board([[int(n) for n in l.split()] for l in s.split('\n')])

def solve(nums: list[int], boards: list[Board]) -> tuple[int, int]:
    won: set[int] = set()
    wins: list[int] = []
    num: int
    for num in nums:
        i: int
        board: Board
        for i, board in enumerate(boards):
            if i in won: continue
            board.call(num)
            if board.has_bingo:
                won.add(i)
                wins.append(num * board.unmarked_sum)
    return wins[0], wins[-1]

# nums: str | list[int]
# boards: list[str] | list[Board]
nums, *boards = open('input.txt').read().rstrip().split('\n\n')
nums = list(map(int, nums.split(',')))
boards = [Board.from_string(b) for b in boards]

part1, part2 = solve(nums, boards)
print(part1) # 14093
print(part2) # 17388