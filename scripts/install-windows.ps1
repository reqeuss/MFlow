$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSScriptRoot
$build = Join-Path $root "build-install"
$prefix = Join-Path $env:LOCALAPPDATA "MFlow"
$bin = Join-Path $prefix "bin"

Write-Host "[1/4] Configuring MFlow..."
cmake -S $root -B $build -DMFLOW_BUILD_TESTS=OFF -DMFLOW_BUILD_BENCHMARKS=OFF -DMFLOW_BUILD_EXAMPLES=OFF

Write-Host "[2/4] Building MFlow..."
cmake --build $build --config Release

Write-Host "[3/4] Installing into $prefix..."
cmake --install $build --config Release --prefix $prefix

Write-Host "[4/4] Updating the user PATH..."
$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
$entries = @($userPath -split ';' | Where-Object { $_ -and $_.Trim() -ne '' })
if ($entries -notcontains $bin) {
    [Environment]::SetEnvironmentVariable("Path", (($entries + $bin) -join ';'), "User")
    Write-Host "Added $bin to the user PATH."
} else {
    Write-Host "$bin is already in the user PATH."
}

Write-Host ""
Write-Host "MFlow was installed successfully."
Write-Host "Close and reopen PowerShell or CMD, then run:"
Write-Host "  mflow version"
