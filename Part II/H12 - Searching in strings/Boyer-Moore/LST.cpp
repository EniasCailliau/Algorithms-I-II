function suffixes($pattern, &$suffixes)
{
   $m = strlen($pattern);
 
   $suffixes[$m - 1] = $m;
   $g = $m - 1;
 
   for ($i = $m - 2; $i >= 0; --$i) {
      if ($i > $g && $suffixes[$i + $m - 1 - $f] < $i - $g) {
         $suffixes[$i] = $suffixes[$i + $m - 1 - $f];
      } else {
         if ($i < $g) {
            $g = $i;
         }
         $f = $i;
 
         while ($g >= 0 && $pattern[$g] == $pattern[$g + $m - 1 - $f]) {
            $g--;
         }
         $suffixes[$i] = $f - $g;
      }
   }
}
 
