import CellWars as cw

class MyBot(cw.PlayerBot):
    def MakeTurn(self, snapshot):
        for field in snapshot.fields.as_list:
            if snapshot.get_adjacent_field_of(field, cw.Direction.up):
                print('Hi')
            else:
                print(field.cell_count)
            """
                field.split_cells(cw.Direction.right, int(field.cell_count * 0.1))
            else:
                field.split_cells(cw.Direction.left, int(field.cell_count * 0.1))
            #field.split_cells(cw.Direction.up,    int(field.cell_count * 0.1))
            """
            field.split_cells(cw.Direction.down,  20)

world     = cw.World()
player_1  = MyBot()
player_2  = cw.PlayerBot()

world.play(player_1, player_2)



"""
if doing something inside of the constructor the constructor of the parent class has to be called
    # def __init__(self):
    #     super(MyBot, self).__init__()
"""
