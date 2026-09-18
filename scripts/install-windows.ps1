$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSScriptRoot
$build = Join-Path $root "build-install"
$prefix = Join-Path $env:LOCALAPPDATA "MFlow"
$bin = Join-Path $prefix "bin"

Write-Host "[1/5] Checking prerequisites..."
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    throw "CMake is required and was not found in PATH."
}

Write-Host "[2/5] Configuring MFlow..."
cmake -S $root -B $build -DMFLOW_BUILD_TESTS=OFF -DMFLOW_BUILD_BENCHMARKS=OFF -DMFLOW_BUILD_EXAMPLES=OFF
if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed." }

Write-Host "[3/5] Building MFlow..."
cmake --build $build --config Release
if ($LASTEXITCODE -ne 0) { throw "MFlow build failed." }

Write-Host "[4/5] Installing into $prefix..."
cmake --install $build --config Release --prefix $prefix
if ($LASTEXITCODE -ne 0) { throw "MFlow installation failed." }

Write-Host "[5/5] Updating the user PATH..."
$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($null -eq $userPath) { $userPath = "" }

$entries = @(
    $userPath -split ';' |
    ForEach-Object { $_.Trim() } |
    Where-Object { $_ -ne '' }
)

if ($entries -notcontains $bin) {
    [Environment]::SetEnvironmentVariable("Path", (($entries + $bin) -join ';'), "User")
    Write-Host "Added $bin to the user PATH."
} else {
    Write-Host "$bin is already in the user PATH."
}

# Also update the current PowerShell process so mflow is immediately usable.
if (($env:Path -split ';') -notcontains $bin) {
    $env:Path = "$bin;$env:Path"
}

Write-Host ""
Write-Host "MFlow 0.4.1 installed successfully."
Write-Host "Installation directory: $prefix"
Write-Host ""
Write-Host "You can now run:"
Write-Host "  mflow version"
Write-Host "  mflow info"
Write-Host ""
Write-Host "The command is available from any directory."
