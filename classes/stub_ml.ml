(** OCaml implementation for foreign stubs. *)

module type Show = sig
  type t

  val show : t -> string
end

module type Eq = sig
  type t

  val eq : t -> t -> bool
end

module type ShowEq = sig
  include Show

  include Eq with type t := t
end

external fooC : ('t -> string) -> ('t -> 't -> bool) -> 't -> 't -> unit
  = "foo_ML_stub"

let foo (type a) (module M : ShowEq with type t = a) x y = fooC M.show M.eq x y

external barC : ('t -> string) -> 't -> unit = "bar_ML_stub"

let bar (type a) (module M : Show with type t = a) x = barC M.show x
