drop table if exists NonPlayerCharacter;
drop table if exists NonPlayerCharacterPath;
drop table if exists BoundingBox;
drop table if exists MapObject;
drop table if exists Container;
drop table if exists Hardpoints;
drop table if exists Tiles;

create table NonPlayerCharacter
(
   MapObjectId integer(10) not null,
   speed integer(10) null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table NonPlayerCharacterPath
(
   MapObjectId integer(10) not null,
   WC_X integer(10) not null,
   WC_Y integer(10) not null,
   PathIndex integer(10) not null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
   
);

create table BoundingBox
(
   BoundingBoxID integer(10) not null,
   WC_X integer(10) null,
   WC_Y integer(10) null,
   Height integer(10) null,
   Width integer(10) null
);

create table MapObject
(
   MapObjectID integer(10) not null,
   WC_X integer(10) null,
   WC_Y integer(10) null,
   Height integer(10) null,
   Width integer(10) null,
   BoundingBoxID integer(10) null,
   primary key(MapObjectID)
);

create table Container
(
   MapObjectID integer(10) null,
   item0 integer(10) null,
   item1 integer(10) null,
   item2 integer(10) null,
   item3 integer(10) null,
   item4 integer(10) null,
   item5 integer(10) null,
   item6 integer(10) null,
   item7 integer(10) null,
   item8 integer(10) null,
   item9 integer(10) null,
   item10 integer(10) null,
   item11 integer(10) null,
   item12 integer(10) null,
   item13 integer(10) null,
   item14 integer(10) null,
   foreign key(MapObjectID) references MapObject(MapObjectID)
);

create table Hardpoints
(
   MapObjectId integer(10) not null,
   RelativeX integer(10) not null,
   RelativeY integer(10) not null,
   HardpointType integer(10) not null,
   Width integer(10) null,
   Height integer(10) null,
   Radius integer(10) null,
   primary key (MapObjectId, RelativeX, RelativeY, HardpointType),
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table Tiles
(
   MapObjectID integer(10) not null,
   TileType integer(10) null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
);
