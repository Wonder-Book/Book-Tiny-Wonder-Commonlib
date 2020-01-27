let createEmpty = (): Js.Dict.t(Js.Nullable.t('a)) => Js.Dict.empty();

let unsafeGetByNull = (key: string, map) =>
  Js.Dict.unsafeGet(map, key) |> HashMapType.nullableToNotNullable;

let get = (key: string, map) => {
  let value = Js.Dict.unsafeGet(map, key);
  NullUtils.isEmpty(value)
    ? None : Some(value |> HashMapType.nullableToNotNullable);
};

let has = (key: string, map) =>
  !NullUtils.isEmpty(Js.Dict.unsafeGet(map, key));

let entries =
    (map: Js.Dict.t(Js.Nullable.t('a))): array((Js.Dict.key, 'a)) =>
  map |> Js.Dict.entries |> HashMapType.entriesNullableToEntriesNotNullable;

let fastGetByNull = (key, map: Js.Dict.t(Js.Nullable.t('a))) => {
  let value = Js.Dict.unsafeGet(map, key);

  (NullUtils.isInMap(value), value |> HashMapType.nullableToNotNullable);
};

let getValidEntries =
    (map: Js.Dict.t(Js.Nullable.t('a))): array((Js.Dict.key, 'a)) =>
  map
  |> entries
  |> HashMapType.entriesNotNullableToEntriesNullable
  |> Js.Array.filter(((_, value)) => value |> NullUtils.isInMap)
  |> HashMapType.entriesNullableToEntriesNotNullable;

let _mutableSet = (key: string, value, map) => {
  Js.Dict.set(map, key, value);
  map;
};

let _createEmpty = (): Js.Dict.t('a) => Js.Dict.empty();

let copy =
    (map: Js.Dict.t(Js.Nullable.t('a))): Js.Dict.t(Js.Nullable.t('a)) =>
  map
  |> entries
  |> ArrayUtils.reduceOneParam(
       (. newMap, (key, value)) => newMap |> _mutableSet(key, value),
       _createEmpty(),
     )
  |> HashMapType.dictNotNullableToDictNullable;