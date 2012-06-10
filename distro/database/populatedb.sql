--Tropical Island Demo

--Palm Tree 1 (id = 1)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,3,175,"PalmTree");

--Treasure Chest (id = 2)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,40,40,"TreasureChest");

--Hand (id = 3)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,430,170,"HandSwingsSword");

-- Puddle (id = 4)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,100,500,"Puddle");

--Palm Tree 2 (id = 5)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,1300,250,"PalmTree");

--Palm Tree 3 (id = 6)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,1100,500,"PalmTree");

--Palm Tree 4 (id = 7)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,1050,1100,"PalmTree");

--Palm Tree 5 (id = 8)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,700,1217,"PalmTree");

--Treasure Chest 1 (id = 9)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,700,400,"TreasureChest");

--Treasure Chest 2 (id = 10)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,1200,500,"TreasureChest");

--Rock 1 (id = 11)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,250,250,"Rock");

--Rock 2 (id = 12)
insert into MapObject
(MapObjectId,WC_X,WC_Y,DrawableName)
values(NULL,550,150,"Rock");

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

--Palm Tree #1's Hardpoints
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,47,224,14,8); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,61,219,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,63,205,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,67,192,20,39); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,85,222,10,14); --Rect
--End Palm Tree #1's Hardpoints

--Treasure Chest's Hardpoint
--Hardpoint Type = 0 = RectHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(2,0,6,31,62,20);

--Hand's Hardpoint
--Hardpoint Type = 1 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(3,1,0,0,3);

--Palm Tree #2's Hardpoints
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(5,0,47,224,14,8); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(5,0,61,219,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(5,0,63,205,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(5,0,67,192,20,39); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(5,0,85,222,10,14); --Rect
--End Palm Tree #2's Hardpoints

--Palm Tree #3's Hardpoints
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(6,0,47,224,14,8); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(6,0,61,219,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(6,0,63,205,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(6,0,67,192,20,39); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(6,0,85,222,10,14); --Rect
--End Palm Tree #3's Hardpoints

--Palm Tree #4's Hardpoints
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(7,0,47,224,14,8); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(7,0,61,219,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(7,0,63,205,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(7,0,67,192,20,39); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(7,0,85,222,10,14); --Rect
--End Palm Tree #4's Hardpoints

--Palm Tree #5's Hardpoints
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(8,0,47,224,14,8); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(8,0,61,219,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(8,0,63,205,7,15); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(8,0,67,192,20,39); --Rect
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(8,0,85,222,10,14); --Rect
--End Palm Tree #5's Hardpoints

--Treasure Chest's Hardpoint
--Hardpoint Type = 0 = RectHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(9,0,6,31,62,20);

--Treasure Chest's Hardpoint
--Hardpoint Type = 0 = RectHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(10,0,6,31,62,20);

--Rock's Hardpoint
--Hardpoint Type = 1 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,0,0,3);

--Rock #1's Hardpoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,18,51,11);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,13,63,9);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,22,67,15);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,34,70,9);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,46,67,9);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,65,72,16);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,71,81,12);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,121,80,12);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(11,1,128,70,12);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(11,0,72,77,48,17);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(11,0,16,39,125,21);
--End Rock #1's Hardpoints

--Rock #2's Hardpoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,18,51,11);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,13,63,9);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,22,67,15);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,34,70,9);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,46,67,9);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,65,72,16);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,71,81,12);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,121,80,12);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(12,1,128,70,12);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(12,0,72,77,48,17);
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Width,Height)
values(12,0,16,39,125,21);
--End Rock #2's Hardpoints

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

insert into Drawable
(DrawableName,AnimationName)
values("Rock","Rock");

insert into Drawable
(DrawableName,AnimationName)
values("NotMatch","NotMatch");

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

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("palmtree.png",11,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("treasurechest.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("rock.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchStandingEast.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchStandingWest.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchWalkingWest.png",7,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchWalkingEast.png",7,1);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("HandSwingsSwordSouth","HandSwingsSwordSouth.bmp",100,50,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("HandSwingsSwordNorth","HandSwingsSwordNorth.bmp",100,50,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("HandSwingsSwordEast","HandSwingsSwordEast.bmp",100,50,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("HandSwingsSwordWest","HandSwingsSwordWest.bmp",100,50,4);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("PalmTree","palmtree.png",240,170,6);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("Puddle","OsirisCat.png",75,25,5);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("TreasureChest","treasurechest.png",55,75,1);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("OsirisCat","OsirisCat.png",75,25,9);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("Rock","rock.png",96,145,1);
