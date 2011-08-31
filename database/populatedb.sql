--Tropical Island Demo

--Palm Tree (id = 1)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,DrawableName)
values(NULL,3,175,25,5,"PalmTree");

--Treasure Chest (id = 2)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,DrawableName)
values(NULL,40,40,3,7,"TreasureChest");

--Hand (id = 3)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,DrawableName)
values(NULL,430,170,3,3,"HandSwingsSword");

-- Puddle (id = 4)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,DrawableName)
values(NULL,100,500,2,2,"Puddle");

--Treasure Chest's Container (Saftey Match)
insert into Container
(MapObjectId,item0)
values(2,1);

--Hand's NPC
insert into NonPlayerCharacter
(MapObjectId,Speed)
values(3,1);

--Puddle's Tile
insert into Tiles
(MapObjectId,TileType)
values(4,0);

--Hand's NPC Path
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(3,43,43,0);
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(3,33,25,1);
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(3,55,3,2);
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(3,23,47,3);

--Palm Tree's Hardpoint
--Hardpoint Type = 1 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(1,1,0,0,3);

--Treasure Chest's Hardpoint
--Hardpoint Type = 0 = RectHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Height,Width)
values(2,0,0,0,5,5);

--Hand's Hardpoint
--Hardpoint Type = 1 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(3,1,0,0,3);

--Hand's Animations
--Hand swings sword
insert into Drawable
(DrawableName,AnimationName)
values("HandSwingsSword","HandSwingsSwordSouth");

insert into Drawable
(DrawableName,AnimationName)
values("HandSwingsSword","HandSwingsSwordNorth");

insert into Drawable
(DrawableName,AnimationName)
values("HandSwingsSword","HandSwingsSwordEast");

insert into Drawable
(DrawableName,AnimationName)
values("HandSwingsSword","HandSwingsSwordWest");

insert into Drawable
(DrawableName,AnimationName)
values("PalmTree","PalmTree");

insert into Drawable
(DrawableName,AnimationName)
values("Puddle","Puddle");

insert into Drawable
(DrawableName,AnimationName)
values("TreasureChest","TreasureChest");

insert into Drawable
(DrawableName,AnimationName)
values("OsirisCat","OsirisCat");

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordSouth.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordNorth.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordEast.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordWest.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("OsirisCat.png",3,1);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("HandSwingsSwordSouth","HandSwingsSwordSouth.bmp",100,50,4,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("HandSwingsSwordNorth","HandSwingsSwordNorth.bmp",100,50,4,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("HandSwingsSwordEast","HandSwingsSwordEast.bmp",100,50,4,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("HandSwingsSwordWest","HandSwingsSwordWest.bmp",100,50,4,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("PalmTree","OsirisCat.png",75,25,3,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("Puddle","OsirisCat.png",75,25,3,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("TreasureChest","OsirisCat.png",75,25,3,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillCount,StillsPerSecond)
values("OsirisCat","OsirisCat.png",75,25,3,4);
