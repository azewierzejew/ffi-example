(** Usage for Haskell polymorphic functions. *)

open Stub_ml

module Integer : sig
  type t = int

  include Show with type t := t

  include Eq with type t := t
end = struct
  type t = int

  let show x = "OCaml (" ^ string_of_int x ^ ")"

  let eq x y = x == y
end

module Float : sig
  type t = float

  include Show with type t := t

  include Eq with type t := t
end = struct
  type t = float

  let show x = "OCaml (" ^ string_of_float x ^ ")"

  let eq x y = x == y
end

module String : sig
  type t = string

  include Show with type t := t

  include Eq with type t := t
end = struct
  type t = string

  let show x = "OCaml (" ^ x ^ ")"

  let eq x y = x == y
end

let _ =
  let x = 5 in
  let y = 7 in
  let a = 1.0 in
  let b = 3.5 in
  foo (module Integer) x y;
  foo (module Integer) x x;
  (* The following doesn't work *)
  (* foo (module Integer) (module Integer) a y; *)
  foo (module Float) a b;
  foo (module Float) a a;
  bar (module Integer) x;
  bar (module Integer) y;
  bar (module Float) a;
  bar (module Float) b;
  foo (module String) "Hello" "world";
  bar (module String) "Hello world";
  ()
