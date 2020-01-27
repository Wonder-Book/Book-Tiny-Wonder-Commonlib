type t('a) = Js.Dict.t(Js.Nullable.t('a));

type t2('key, 'a) = Js.Dict.t(Js.Nullable.t('a));

let createEmpty = HashMap.createEmpty;

let set = (key: string, value: 'a, map: t('a)): t('a) => {
  let newMap = map |> HashMap.copy;

  Js.Dict.set(newMap, key, value |> HashMapType.notNullableToNullable);

  newMap;
};

let get = HashMap.get;

let unsafeGetByNull = HashMap.unsafeGetByNull;

let fastGetByNull = HashMap.fastGetByNull;

let has = HashMap.has;

let getValidEntries = HashMap.getValidEntries;