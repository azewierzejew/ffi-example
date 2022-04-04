module type Show = sig
  type t

  val show : t -> string
end

module type Eq = sig
  type t

  val eq : t -> t -> bool
end

val foo :
  (module Show with type t = 't) ->
  (module Eq with type t = 't) ->
  't ->
  't ->
  unit

val bar : (module Show with type t = 't) -> 't -> unit
