--Tropical Island
insert into BoundingBox
(BoundingBoxId,WC_X,WC_Y,Height,Width)
values(NULL,0,0,100,100);

--Palm Tree (id = 1)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,BoundingBoxId)
values(NULL,3,5,5,5,1);

--Treasure Chest (id = 2)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,BoundingBoxId)
values(NULL,40,40,3,7,1);

--Hand (id = 3)
insert into MapObject
(MapObjectId,WC_X,WC_Y,Height,Width,BoundingBoxId)
values(NULL,23,47,3,3,1);

--Treasure Chest's Container (Saftey Match)
insert into Container
(item0)
values(1);

--Hand's NPC
insert into NonPlayerCharacter
(MapObjectId,Speed)
values(3,1);

--Hand's NPC Path
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(1,43,43,0);
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(1,33,25,1);
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(1,55,3,2);
insert into NonPlayerCharacterPath
(MapObjectId,WC_X,WC_Y,PathIndex)
values(1,23,47,3);

--Palm Tree's Hardpoint
--Hardpoint Type = 2 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(1,2,0,0,3);

--Treasure Chest's Hardpoint
--Hardpoint Type = 1 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Height,Width)
values(2,1,0,0,5,5);

--Hand's Hardpoint
--Hardpoint Type = 2 = CircHardPoint
insert into Hardpoints
(MapObjectId,HardpointType,RelativeX,RelativeY,Radius)
values(3,2,0,0,3);
