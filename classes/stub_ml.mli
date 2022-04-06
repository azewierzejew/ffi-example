(** Interface for foreign stubs. *)

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

val foo :
  (module ShowEq with type t = 't) ->
  't ->
  't ->
  unit

val bar : (module Show with type t = 't) -> 't -> unit
