module type Show = sig
  type t

  val show : t -> string
end

module type Eq = sig
  type t

  val eq : t -> t -> bool
end

external fooC : ('t -> string) -> ('t -> 't -> bool) -> 't -> 't -> unit
  = "foo_ML_stub"

let foo (type a) (module Show : Show with type t = a)
    (module Eq : Eq with type t = a) x y =
  fooC Show.show Eq.eq x y

external barC : ('t -> string) -> 't -> unit = "bar_ML_stub"

let bar (type a) (module Show : Show with type t = a) x = barC Show.show x
