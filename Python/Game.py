import CellWars as cw

class MyBot(cw.PlayerBot):
    def MakeTurn(self, snapshot):
        for field in snapshot.fields.as_list:
            field.split_all_directions(24)
            # field.split(cw.Direction.up,20)


world     = cw.World()
player_1  = MyBot()
player_2  = cw.PlayerBot()

world.play(player_1, player_2)

"""
if doing something inside of the constructor the constructor of the parent class has to be called
    # def __init__(self):
    #     super(MyBot, self).__init__()
"""
