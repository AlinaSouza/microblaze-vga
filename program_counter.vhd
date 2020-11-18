library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity program_counter is

	Port (
		clk : in STD_LOGIC;
		ena : in STD_LOGIC;
		addr : out STD_LOGIC_VECTOR (13 downto 0)
	);

end program_counter;

architecture Behavioral of program_counter is

	signal pc : unsigned(13 downto 0) := (others => '0');

begin

	increment : process(clk)
	begin
		if rising_edge(clk) then
			if ena = '1' then
				pc <= pc + 1;
			end if;
		end if;
	end process;

	addr <= std_logic_vector(pc);
	
end Behavioral;
