var parameters = null;
var source     = "";
var total      = 255;

/* ... */
function next() {
  var p = parameters;

  // ...
  if (null === p) {
    parameters = {classed: false, cmem: false, constant: false, pointer: false, reference: false, variadic: false, vmem: false, volatile: false};
    return parameters
  }

  if (p.variadic) p.variadic = false;
  else { p.variadic = true; return parameters }

  if (null !== p.pointer) {
    if (!p.classed && !p.cmem && !p.constant && !p.pointer && !p.reference && !p.vmem && !p.volatile) { p.pointer  = true;  return parameters }
    if (!p.classed && !p.cmem && !p.constant &&  p.pointer && !p.reference && !p.vmem && !p.volatile) { p.constant = true;  return parameters }
    if (!p.classed && !p.cmem &&  p.constant &&  p.pointer && !p.reference && !p.vmem && !p.volatile) { p.volatile = true;  return parameters }
    if (!p.classed && !p.cmem &&  p.constant &&  p.pointer && !p.reference && !p.vmem &&  p.volatile) { p.constant = false; return parameters }
    if (!p.classed && !p.cmem && !p.constant &&  p.pointer && !p.reference && !p.vmem &&  p.volatile) { p.pointer  = null; p.volatile = false }
  }
  
  if (null !== p.reference) {
    if (!p.classed && !p.cmem && !p.constant && !p.reference && !p.vmem && !p.volatile) { p.reference = true; return parameters }
    if (!p.classed && !p.cmem && !p.constant &&  p.reference && !p.vmem && !p.volatile) p.reference = null
  }

  if (null !== p.classed) {
    if (!p.classed && !p.cmem && !p.constant && !p.vmem && !p.volatile) { p.classed = true;                   return parameters }
    if ( p.classed && !p.cmem && !p.constant && !p.vmem && !p.volatile) { p.cmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem && !p.constant && !p.vmem && !p.volatile) { p.vmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem && !p.constant &&  p.vmem && !p.volatile) { p.cmem    = false;                  return parameters }
    if ( p.classed && !p.cmem && !p.constant &&  p.vmem && !p.volatile) { p.constant = true; p.vmem = false;  return parameters }
    if ( p.classed && !p.cmem &&  p.constant && !p.vmem && !p.volatile) { p.cmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem &&  p.constant && !p.vmem && !p.volatile) { p.vmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem &&  p.constant &&  p.vmem && !p.volatile) { p.cmem    = false;                  return parameters }
    if ( p.classed && !p.cmem &&  p.constant &&  p.vmem && !p.volatile) { p.volatile = true; p.vmem = false;  return parameters }
    if ( p.classed && !p.cmem &&  p.constant && !p.vmem &&  p.volatile) { p.cmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem &&  p.constant && !p.vmem &&  p.volatile) { p.vmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem &&  p.constant &&  p.vmem &&  p.volatile) { p.cmem    = false;                  return parameters }
    if ( p.classed && !p.cmem &&  p.constant &&  p.vmem &&  p.volatile) { p.constant = false; p.vmem = false; return parameters }
    if ( p.classed && !p.cmem && !p.constant && !p.vmem &&  p.volatile) { p.cmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem && !p.constant && !p.vmem &&  p.volatile) { p.vmem    = true;                   return parameters }
    if ( p.classed &&  p.cmem && !p.constant &&  p.vmem &&  p.volatile) { p.cmem    = false;                  return parameters }
    if ( p.classed && !p.cmem && !p.constant &&  p.vmem &&  p.volatile) { p.classed = null; p.volatile = false; p.vmem = false }
  }

  parameters = null;
  return null
}

// classed   [...]
// cmem
// constant
// pointer   [...]
// reference [...]
// variadic
// vmem
// volatile
for (var count = 0; count !== total + 1; ++count)
for (var p = next(); null !== parameters; next()) {
  var control   = "";
  var subsource = "";

  // ...
  control   += "template <typename type, class object, ";
  subsource += "template <typename type, " + (p.classed ? "class object, " : "");
  if (0 === count) subsource = subsource.slice(0, -2);

  for (var subcount = 0; subcount !== total; ++subcount) { control   += "typename type" + (subcount + 1) + (subcount === total - 1 ? "" : ", ") } control   += '>';
  for (var subcount = 0; subcount !== count; ++subcount) { subsource += "typename type" + (subcount + 1) + (subcount === count - 1 ? "" : ", ") } subsource += '>';
  for (var subcount = control.length - subsource.length; subcount && --subcount; ) subsource += ' ';

  // ...
  control   += "struct assess_functional<type (object::* const volatile)";
  subsource += "struct assess_functional<type ";
    if (p.classed)
    subsource += "(object::*" + ((p.constant ? "const " : "") + (p.volatile ? "volatile " : "")).trimRight() + ')' + (p.constant && p.volatile ? "" : ' ') + (p.constant ? "" : "     ") + (p.volatile ? "" : "        ");

    if (p.pointer)
    subsource += "(*" + ((p.constant ? "const " : "") + (p.volatile ? "volatile " : "")).trimRight() + ')' + (p.constant && p.volatile ? "" : ' ') + (p.constant ? "" : "     ") + (p.volatile ? "" : "        ") + "        ";

    if (p.reference)
    subsource += "(&)" + "                      ";

    if (!(p.classed || p.pointer || p.reference))
    subsource += "                         ";
  subsource += '(';

  for (var subcount = 0; subcount !== total; ++subcount) { control   += "type" + (subcount + 1) + (subcount === total - 1 ? "" : ", ") }
  control   += ", ...) ";
  
  for (var subcount = 0; subcount !== count; ++subcount) { subsource += "type" + (subcount + 1) + (subcount === count - 1 ? "" : ", ") }
  subsource += (p.variadic ? (0 === count ? "" : ", ") + "..." : "") + ") ";
  subsource += false === p.variadic ? (0 === count ? "" : "  ") + "   " : "";
  for (var subcount = control.length - subsource.length; subcount; --subcount) subsource += ' ';

  subsource += ((p.cmem ? "const " : "") + (p.vmem ? "volatile " : "")).trimRight();
  control += "const volatile";
  for (var subcount = control.length - subsource.length; subcount; --subcount) subsource += ' ';

  // ...
  subsource += "> final { typedef type base; static std::size_t const arity = " + count + "u; static bool const constness = " + (p.cmem ? "true, " : "false,") + " except = true, lvalue = " + (p.classed ? "true, " : "false,") + " member = " + (p.classed ? "true, " : "false,") + " rvalue = false, variadic = " + (p.variadic ? "true, " : "false,") + " volatileness = " + (p.vmem ? "true; " : "false;") + " };";
  source += subsource + '\n'
}

/* ... */
document.open();
document.write("<h1> " + source.length + " </h1> <pre>" + source.replace(/\</g, "&lt;").replace(/\>/g, "&gt;") + "</pre>");
document.close()
