external fibC : int -> int = "fibC_stub"

let rec fibML n =
  Printf.printf "Fib OCaml: %d\n%!" n;
  if n <= 1 then n
  else
    let c = fibC (n - 2) in
    let ml = fibML (n - 1) in
    c + ml


let _ = Callback.register "fibML" fibML
